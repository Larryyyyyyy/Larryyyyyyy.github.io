const inputEmail=document.getElementById('inputEmail1');
const inputPassword=document.getElementById('inputPassword1');
let legal;
let legal_Email;
let legal_Password;

// 验证密码规范
function judgePassword(){
	let _password=inputPassword.value;
	if(_password==null||_password==='')legal_Password=false;
}

// 验证邮箱规范
function judgeEmail(){
	let email=inputEmail.value;
	if(!email.match(/^\w+@\w+\.\w+$/i))legal_Email=false;
}

// 开始验证
function judge(){
	legal=false;
	legal_Email=true;
	legal_Password=true;
	judgePassword();
	judgeEmail();
	if(legal_Email&&legal_Password)legal=true;
	if(legal){
		// 连接数据库等等
	}
	else{
		// 回弹错误信息
		let Error="";
		if(!legal_Email){
			Error+="Your email is illegal or blank.\n";
		}
		if(!legal_Password){
			Error+="Password should not be blank.\n";
		}
		alert(Error);
	}
}
// 控制按钮事件绑定
loginConfirm.addEventListener('click', judge);
