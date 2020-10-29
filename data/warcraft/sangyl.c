// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("炙炎飞鸿[2;37;0m[2;37;0m", ({"yanglin"}));        
        set("gender", "女性");                
        set("long", "炙炎飞鸿[2;37;0m
它是桑杨林的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sangyl");
        set("owner_name", "桑杨林");
        set_temp("owner", "sangyl");
        set_temp("owner_name", "桑杨林");
        ::setup();
}
