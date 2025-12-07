function CheckOwnerCode()
{
	let result = /^[A-Z]{3}$/.test(document.getElementsByName('owner_code')[0].value);
	
	if (result == false)
		alert('Введён некорректный код владельца!');

	return result;
}

function CheckSerial()
{
	let result = /^[0-9]{6}$/.test(document.getElementsByName('serial')[0].value);
	
	if (result == false)
		alert('Введён некорректный серийный номер!');

	return result;
}

function CheckControlNumber()
{
	let result = /^[0-9]$/.test(document.getElementsByName('control_number')[0].value);
	
	if (result == false)
		alert('Введено некорректное контрольное число!');

	return result;
}

function CheckCountryCode()
{
	let result = /^[A-Z]{2}$/.test(document.getElementsByName('country_code')[0].value);

	if (result == false)
		alert('Введен некорректный код страны!');

	return result;
}

function CheckSizeCode()
{
	let result = /^[A-Z0-9]{2}$/.test(document.getElementsByName('size_code')[0].value);

	if (result == false)
		alert('Введен некорректный код внешних габаритов!');

	return result;
}

function CheckCargoWeight()
{
	let result = document.getElementsByName('cargo_weight')[0].valueAsNumber > 0;

	if (result == false)
		alert('Введена некорректная масса брутто!');

	return result;
}

function CheckContainerWeight()
{
	let result = document.getElementsByName('container_weight')[0].valueAsNumber > 0;

	if (result == false)
		alert('Введена некорректная масса тары!');

	return result;
}

function CheckUsefull()
{
	let result = document.getElementsByName('usefull')[0].valueAsNumber > 0;

	if (result == false)
		alert('Введена некорректная грузоподъёмность!');

	return result;
}

function CheckSpace()
{
	let result = document.getElementsByName('space')[0].valueAsNumber > 0;

	if (result == false)
		alert('Введена некорректная вместимость!');

	return result;
}

function CheckAddingContainer()
{
	return CheckOwnerCode() && CheckSerial() && CheckControlNumber() && 
           CheckCountryCode() && CheckSizeCode() && CheckCargoWeight() && 
           CheckContainerWeight() && CheckUsefull() && CheckSpace();
}