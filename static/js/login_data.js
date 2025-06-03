const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const bodyParser = require('body-parser');

const app = express();
const port = 3000;
const cors = require('cors');
app.use(cors());


// 解析 JSON 请求体
app.use(bodyParser.json());

// 连接 SQLite 数据库
const db = new sqlite3.Database('./database.db');

// 创建一个简单的表格（如果数据库中不存在）
db.serialize(() => {
    db.run("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT, password TEXT)");
});

// 处理前端表单提交的 POST 请求
app.post('/submit', (req, res) => {
    console.log('收到的请求体:', req.body); // 日志输出
    const { inputEmail1,inputPassword1 } = req.body;

    if (!inputPassword1 || !inputEmail1) {
        console.error("Lack of password and email"); // 输出错误日志
        return res.status(400).json({ error: '缺少密码或邮箱' });
    }

    const stmt = db.prepare("INSERT INTO users (email,password) VALUES (?, ?)");
    stmt.run(inputEmail1,inputPassword1, function(err) {
        if (err) {
            console.error('数据库插入失败:', err); // 输出错误日志
            return res.status(500).json({ error: '插入数据失败', details: err });
        }
        console.log('数据已插入，用户ID:', this.lastID); // 插入成功日志
        res.status(200).json({ message: '数据已成功插入', userId: this.lastID });
    });
    stmt.finalize();
});


// 启动服务器
app.listen(port, () => {
    console.log(`服务器正在运行，访问地址: http://localhost:${port}`);
});
