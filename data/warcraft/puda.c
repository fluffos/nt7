// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m拳打卧牛之地[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIB$拳打卧牛之地[2;37;0m
它是菩达的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "puda");
        set("owner_name", "菩达");
        set_temp("owner", "puda");
        set_temp("owner_name", "菩达");
        ::setup();
}
