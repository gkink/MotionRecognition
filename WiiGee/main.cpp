//
//  main.cpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <ctime>

#include <typeinfo>




int main()
{
    auto timePoint = std::chrono::system_clock::now().time_since_epoch();
    
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint).count();
    
    std::cout << millis <<std::endl;
    
    long long t = millis;
    
    std::cout << sizeof(t);
    
    std::cout << typeid(long).name() << '\n';
    
}