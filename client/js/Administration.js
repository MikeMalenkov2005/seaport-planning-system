module.controller("BidListCont", function($scope, $http)
{
    $http.get("https://" + window.location.host + "/bid.cgi")
    .then(function(response)
    {
		$scope.st_list = ["Принята", "Отказ", "Направлена в таможню", "Направлена на склад", 
		"Направлена диспетчеру", "Направлена стивидору", "Обрабатывается в таможне",
		"Обрабатывается на складе", "Обрабатывается диспетчером", "Обрабатывается стивидором"];
		
        $scope.list = response.data;
    })
    .catch(function(error)
    {
		console.log("Wrong data");
    });
});

module.controller("ShowBidCont", function($scope, $http)
{
	$scope.find = function()
	{
		$http.get("https://" + window.location.host + "/ibid.cgi?id=" + document.getElementById("id").value)
		.then(function(response)
		{
			st_list = ["Принята", "Отказ", "Направлена в таможню", "Направлена на склад", 
			"Направлена диспетчеру", "Направлена стивидору", "Обрабатывается в таможне",
			"Обрабатывается на складе", "Обрабатывается диспетчером", "Обрабатывается стивидором"];
			
			tr_list = ["Авто", "Ж/Д", "Водный"];
		
			dr_list = ["Экспорт", "Импорт"];
			
			wr_list = ["Крытый", "Открытый"];
		
			// Заполнение ВСЕХ полей из response.data
			$scope.org = response.data.org;
			$scope.inn = response.data.inn;
			$scope.phone = response.data.phone;
			$scope.email = response.data.email;
			$scope.name = response.data.name;
			$scope.toved = response.data.toved;
			$scope.direction = dr_list[response.data.direction-1]; //
			$scope.length = response.data.length;
			$scope.width = response.data.width;
			$scope.height = response.data.height;
			$scope.weight = response.data.weight;
			$scope.count = response.data.count;
			$scope.packaging = response.data.packaging;
			$scope.characteristics = response.data.characteristics;
			$scope.transport_in = tr_list[response.data.transport_in-1];
			$scope.transport_out = tr_list[response.data.transport_out-1];
			$scope.date_out = response.data.date_out;
			$scope.date_in = response.data.date_in;
			$scope.warehouse_type = wr_list[response.data.warehouse_type-1];
			$scope.shelf_life = response.data.shelf_life;
			$scope.demands = response.data.demands;
			$scope.creator = response.data.creator;
			$scope.sender = response.data.sender;
			$scope.sender_port = response.data.sender_port;
			$scope.sender_country = response.data.sender_country;
			$scope.receiver_port = response.data.receiver_port;
			$scope.receiver_country = response.data.receiver_country;
			$scope.receiver = response.data.receiver;
			$scope.other = response.data.other;
			$scope.comment = response.data.comment;
			$scope.status = st_list[response.data.status-1];
		})
		.catch(function(error)
		{
			console.log("Wrong data");
		});
	}
});

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
    
    let result = inputDate.getTime() >= today.getTime();
    
    if (!result) {
        alert("Введена некорректная дата завоза!");
    }
    
    return result;
}

function CheckDateOut()
{
	let inputDate = new Date(document.getElementsByName('date_out')[0].value);
    let today = new Date();
    
    let result = inputDate.getTime() >= getTime();
    
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