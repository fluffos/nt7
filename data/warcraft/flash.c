// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[34m蓝狐[2;37;0m[2;37;0m", ({"bluefox"}));        
        set("gender", "女性");                
        set("long", "$BLU$蓝狐[2;37;0m
它是动漫儿的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "flash");
        set("owner_name", "动漫儿");
        set_temp("owner", "flash");
        set_temp("owner_name", "动漫儿");
        ::setup();
}
