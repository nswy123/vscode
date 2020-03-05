cars = 100                                              #定义车辆总数目
space_in_a_car = 4.0                                    #
drivers = 30                                            #司机数
passengers = 90                                         #乘客数
cars_not_driven = cars - drivers                        #剩余汽车数
cars_driven = drivers                                   #司机数
carpool_capacity = cars_driven * space_in_a_car         #运输人数
average_passengers_per_car = passengers / cars_driven   #平均每辆车上的人数


print("there are", cars, "cars available")
print("there are only",drivers, "drivers available.")
print("there will be", cars_not_driven, "empty cars today.")
print("we can transport", carpool_capacity, "people today.")
print("we have", passengers, "to carpool today.")
print("we need to put about",average_passengers_per_car,"in each car.")
