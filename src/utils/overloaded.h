//
// Created by Andrii Klykavka on 09.07.2025.
//

#ifndef OVERLOADED_H
#define OVERLOADED_H

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};


#endif //OVERLOADED_H
