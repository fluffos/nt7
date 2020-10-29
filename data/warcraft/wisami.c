// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m幻[1;33m情[2;37;0m[2;37;0m[2;37;0m", ({"rkelly"}));        
        set("gender", "女性");                
        set("long", "思念是一种很玄的东西[2;37;0m
它是林水儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wisami");
        set("owner_name", "林水儿");
        set_temp("owner", "wisami");
        set_temp("owner_name", "林水儿");
        ::setup();
}
