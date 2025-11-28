function CheckUsername()
{
	let result = /^[A-Za-z0-9]{12,16}$/.test(document.getElementsByName('username')[0].value);
	
	if (result == false)
		alert("Введено некорректное имя пользователя!");
	
	return result;
}

function CheckPassword()
{
	let result = /^[A-Za-z0-9_!]{12,16}$/.test(document.getElementsByName('password')[0].value);
	
	if (result == false)
		alert("Введён некорректный пароль!");
	
	return result;
}

function CheckLogin()
{
	return CheckUsername() && CheckPassword();
}