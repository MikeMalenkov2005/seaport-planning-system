function CheckOwnerCode()
{
	let result = /^[A-Z]{3}$/.test(document.getElementsByName('owner_code')[0].value);
	
	if (result == false)
		alert('Введён некорректный код владельца!');
}

function CheckSerial()
{
	let result = /^[0-9]{6}$/.test(document.getElementsByName('serial')[0].value);
	
	if (result == false)
		alert('Введён некорректный серийный номер!');
}

function CheckControlNumber()
{
	let result = /^[0-9]$/.test(document.getElementsByName('control_number')[0].value);
	
	if (result == false)
		alert('Введено некорректное контрольное число!');
}