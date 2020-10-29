// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛇二狗[2;37;0m[2;37;0m", ({"eddyeddy"}));        
        set("gender", "男性");                
        set("long", "蛇二狗[2;37;0m
它是蛇二猫的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "eddylion");
        set("owner_name", "蛇二猫");
        set_temp("owner", "eddylion");
        set_temp("owner_name", "蛇二猫");
        ::setup();
}
