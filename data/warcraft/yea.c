// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("独孤九剑[2;37;0m[2;37;0m", ({"yoy"}));        
        set("gender", "男性");                
        set("long", "黑色的[2;37;0m
它是慕容乖乖的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yea");
        set("owner_name", "慕容乖乖");
        set_temp("owner", "yea");
        set_temp("owner_name", "慕容乖乖");
        ::setup();
}
