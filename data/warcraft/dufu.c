// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m少陵野老[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "少陵野老，杜陵布衣[2;37;0m
它是杜甫的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dufu");
        set("owner_name", "杜甫");
        set_temp("owner", "dufu");
        set_temp("owner_name", "杜甫");
        ::setup();
}
