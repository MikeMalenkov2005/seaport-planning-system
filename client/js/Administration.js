function CheckOrganization()
{
	let result = /^ОАО "[A-Za-zА-Яа-я]{8,12}"$/.test(document.getElementsByName('organization')[0].value);
	
	if (result == false)
		alert("Введено некорректное название организации!");
	
	return result;
}

function CheckINN()
{
	let result = /^[0-9]{10}$/.test(document.getElementsByName('INN')[0].value);
	
	if (result == false)
		alert("Введён некорректный ИНН организации!");
	
	return result;
}

function CheckPhone()
{
	let result = /^\+[0-9]\([0-9]{3}\)[0-9]{3}-[0-9]{2}-[0-9]{2}$/.test(document.getElementsByName('phone')[0].value);
	
	if (result == false)
		alert("Введён некорректный номер телефона!");
	
	return result;
}

function CheckCargoName()
{
	let result = /^[A-Za-zА-Яа-я0-9 ]+$/.test(document.getElementsByName('cargo_name')[0].value);
	
	if (result == false)
		alert("Введено некорректное наименование груза!");
	
	return result;
}

function CheckTNVED()
{
	let result = /^[0-9]{10}$/.test(document.getElementsByName('TNVED')[0].value);
	
	if (result == false)
		alert("Введён некорректный код ТН ВЭД!");
	
	return result;
}

function CheckLength()
{
	let result = document.getElementsByName('length')[0].valueAsNumber > 0;
	
	if (result == false)
		alert("Введена некорректная длина единицы груза!");
	
	return result;
}

function CheckWidth()
{
	let result = document.getElementsByName('width')[0].valueAsNumber > 0;
	
	if (result == false)
		alert("Введена некорректная ширина единицы груза!");
	
	return result;
}

function CheckHeight()
{
	let result = document.getElementsByName('height')[0].valueAsNumber > 0;
	
	if (result == false)
		alert("Введена некорректная высота единицы груза!");
	
	return result;
}

function CheckWeight()
{
	let result = document.getElementsByName('weight')[0].valueAsNumber > 0;
	
	if (result == false)
		alert("Введена некорректная масса единицы груза!");
	
	return result;
}

function CheckPackage()
{
	let result = /^[А-Яа-я ]+$/.test(document.getElementsByName('package')[0].value);
	
	if (result == false)
		alert("Введена некорректная упаковка груза!");
	
	return result;
}

function CheckСharacteristics()
{
	let result = /^[А-Яа-я ]+$/.test(document.getElementsByName('characteristics')[0].value);
	
	if (result == false)
		alert("Введены некорректные транспортные характеристики!");
	
	return result;
}

function CheckQuantity()
{
	let result = document.getElementsByName('quantity')[0].valueAsNumber > 0;
	
	if (result == false)
		alert("Введено некорректное количество единиц груза!");
	
	return result;
}

function CheckDateIn()
{
    let inputDate = new Date(document.getElementsByName('date_in')[0].value);
    let today = new Date();
    
    let result = inputDate.toDateString() >= today.toDateString();
    
    if (!result) {
        alert("Введена некорректная дата завоза!");
    }
    
    return result;
}

function CheckDateOut()
{
	let inputDate = new Date(document.getElementsByName('date_out')[0].value);
    let today = new Date();
    
    let result = inputDate.toDateString() >= today.toDateString();
    
    if (!result) {
        alert("Введена некорректная дата вывоза!");
    }
    
    return result;
}

function CheckTerm()
{
	let result = document.getElementsByName('term')[0].valueAsNumber > 0;
	
	if (result == false)
		alert("Введены некорректные сроки хранения!");
	
	return result;
}

function CheckCreator()
{
	let result = /^ОАО "[A-Za-zА-Яа-я]{8,12}"$/.test(document.getElementsByName('creator')[0].value);
	
	if (result == false)
		alert("Введён некорректный производитель!");
	
	return result;
}

function CheckSender()
{
	let result = /^ОАО "[A-Za-zА-Яа-я]{8,12}"$/.test(document.getElementsByName('sender')[0].value);
	
	if (result == false)
		alert("Введён некорректный грузоотправитель!");
	
	return result;
}

function CheckSendPort()
{
	let result = /^[A-Za-zА-Яа-я]{8,12}$/.test(document.getElementsByName('send_port')[0].value);
	
	if (result == false)
		alert("Введён некорректный порт отправления!");
	
	return result;
}

function CheckSendCountry()
{
	let result = /^[A-Za-zА-Яа-я]{8,12}$/.test(document.getElementsByName('send_country')[0].value);
	
	if (result == false)
		alert("Введена некорректная страна отправления!");
	
	return result;
}

function CheckGetPort()
{
	let result = /^[A-Za-zА-Яа-я]{8,12}$/.test(document.getElementsByName('get_port')[0].value);
	
	if (result == false)
		alert("Введён некорректный порт назначения!");
	
	return result;
}

function CheckGetCountry()
{
	let result = /^[A-Za-zА-Яа-я]{8,12}$/.test(document.getElementsByName('get_country')[0].value);
	
	if (result == false)
		alert("Введена некорректная страна назначения!");
	
	return result;
}

function CheckGetter()
{
	let result = /^ОАО "[A-Za-zА-Яа-я]{8,12}"$/.test(document.getElementsByName('getter')[0].value);
	
	if (result == false)
		alert("Введено некорректное название получателя!");
	
	return result;
}

function CheckAddingBid()
{
    return CheckOrganization() && CheckINN() && CheckPhone() && CheckCargoName() && CheckTNVED() &&
           CheckLength() && CheckWidth() && CheckHeight() && CheckWeight() && CheckPackage() &&
           CheckСharacteristics() && CheckQuantity() && CheckDateIn() && CheckDateOut() && CheckTerm() &&
           CheckCreator() && CheckSender() && CheckSendPort() && CheckSendCountry() && CheckGetPort() &&
           CheckGetCountry() && CheckGetter();
}