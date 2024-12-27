package com.example.phonestitch
import android.content.Context
import android.media.MediaScannerConnection
import android.os.Bundle
import android.os.Environment
import android.view.WindowManager
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import com.example.phonestitch.ui.theme.PhoneStitchTheme
import com.stitch.stitchlib.NativeLib
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import java.io.File
import java.text.SimpleDateFormat
import java.util.Date
import java.util.Locale
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Text
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.*
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // 禁止息屏
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)

        setContent {
            PhoneStitchTheme {
                Surface(
                    modifier = Modifier.fillMaxWidth(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    Greeting(applicationContext)
                }
            }
        }
    }
}
@Composable
fun Greeting(context: Context, modifier: Modifier = Modifier) {
    val showDialog = remember { mutableStateOf(false) }
    val elapsedTime = remember { mutableStateOf(0L) } // 记录拼接时间

    Box(
        modifier = Modifier.fillMaxSize(),
        contentAlignment = androidx.compose.ui.Alignment.Center // 居中对齐
    ) {
        Button(
            onClick = {
                MainScope().launch {
                    val startTime = System.currentTimeMillis()
                    try {
                        // 获取用户应用数据目录路径
                        val appDataDir = NativeLib().getUserAppDataDir()
                        Toast.makeText(context, "应用数据目录: $appDataDir", Toast.LENGTH_LONG).show()

                        // 创建 temp 和 output 目录
                        val cacheDir = context.cacheDir
                        val tempDir = File(cacheDir, "temp")
                        val outputDir = File(cacheDir, "output")

                        if (!tempDir.exists()) tempDir.mkdirs()
                        if (!outputDir.exists()) outputDir.mkdirs()

                        // 拷贝 assets/test 下的 jpg 文件到 temp 目录
                        val assetManager = context.assets
                        assetManager.list("test")?.filter { it.endsWith(".jpg") }?.forEach { fileName ->
                            assetManager.open("test/$fileName").use { inputStream ->
                                val outFile = File(tempDir, fileName)
                                outFile.outputStream().use { outputStream ->
                                    inputStream.copyTo(outputStream)
                                }
                            }
                        }

                        // 设置工作目录、XML文件路径和输出路径
                        val workDir = tempDir.absolutePath
                        val xmlFilePath: String? = null
                        val outputPath = File(outputDir, "output.jpg").absolutePath

                        val result = NativeLib().processPanorama(
                            workDir,
                            outputPath,
                            xmlFilePath,
                            4000,        // canvasWidth
                            0.5,         // exposureValue
                            6,           // sieve
                            null,        // mode
                            false,       // fineComposition
                            null         // groundImagePath
                        )
                        elapsedTime.value = System.currentTimeMillis() - startTime

                        if (result == 0) {
                            tempDir.listFiles()?.forEach { it.delete() }

                            val timestamp = SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(Date())
                            val destinationFile = File(
                                Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES),
                                "kuntu_$timestamp.jpg"
                            )
                            File(outputPath).copyTo(destinationFile, overwrite = true)

                            MediaScannerConnection.scanFile(context, arrayOf(destinationFile.toString()), null, null)
                            showDialog.value = true
                        } else {
                            Toast.makeText(context, "拼接失败，错误代码: $result", Toast.LENGTH_LONG).show()
                        }
                    } catch (e: Exception) {
                        Toast.makeText(context, "发生错误：${e.message}", Toast.LENGTH_LONG).show()
                    }
                }
            },
            modifier = modifier
        ) {
            Text(text = "拼接(stitch)")
        }
    }

    if (showDialog.value) {
        AlertDialog(
            onDismissRequest = { showDialog.value = false },
            title = { Text(text = "拼接完成") },
            text = { Text(text = "耗时 ${elapsedTime.value / 1000} 秒。") },
            confirmButton = {
                Button(onClick = { showDialog.value = false }) {
                    Text(text = "确定")
                }
            }
        )
    }
}


@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    PhoneStitchTheme {
        Greeting(context = LocalContext.current)
    }
}
