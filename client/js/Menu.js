var menu_module = angular.module("MenuModule", []);

menu_module.controller("MenuCont", function($scope, $http)
{
    $http.get("https://" + window.location.host + "/role.cgi")
    .then(function(response)
    {
        let role = response.data.role;
        let menu = document.createElement("ul");
        let arr_t = [];
        let arr_l = [];

        if (role == "Администратор")
        {
            arr_t.push("Добавление заявки");
            arr_t.push("Изменение заявки");
            arr_t.push("Удаление заявки");
			arr_t.push("Список заявок");
			arr_t.push("Список контейнеров");
			arr_t.push("Список морских судов");
            arr_t.push("Просмотр заявки");
			arr_t.push("Просмотр контейнера");
			arr_t.push("Просмотр морского судна");
			arr_t.push("Регистрация сотрудника");
			arr_t.push("Изменение данных сотрудника");
			arr_t.push("Удаление данных сотрудника");

            arr_l.push("/html.cgi?page=AddBid");
            arr_l.push("/html.cgi?page=ChangeBid");
            arr_l.push("/html.cgi?page=RemoveBid");
			arr_l.push("/html.cgi?page=BidList");
			arr_l.push("/html.cgi?page=ContainerList");
			arr_l.push("/html.cgi?page=ShipList");
            arr_l.push("/html.cgi?page=ShowBid");
			arr_l.push("/html.cgi?page=ShowContainer");
			arr_l.push("/html.cgi?page=ShowShip");
			arr_l.push("/html.cgi?page=AddUser");
			arr_l.push("/html.cgi?page=ChangeUser");
			arr_l.push("/html.cgi?page=RemoveUser");
        }
        else if (role == "Таможенник")
        {
			arr_t.push("Работа с заявкой");
            arr_t.push("Список заявок");
            arr_t.push("Просмотр заявки");
			
			arr_l.push("/html.cgi?page=SearchBidWork");
            arr_l.push("/html.cgi?page=BidList");
            arr_l.push("/html.cgi?page=ShowBid");
        }
        else if (role == "Тальман")
        {

        }
        else if (role == "Диспетчер")
        {

        }
        else if (role == "Стивидор")
        {

        }

        for (let i = 0; i < arr_t.length(); i++)
        {
            let elem1 = document.createElement("li");
			let elem2 = document.createElement("a")

            elem2.setAttribute("href", arr_l[i]);
            elem2.innerHTML = arr_t[i];
			elem1.appendChild(elem2);
            menu.appendChild(elem1);
        }
		
		document.getElementById("navigation").appendChild(menu);
    })
    .catch(function(error)
    {

    });
});
