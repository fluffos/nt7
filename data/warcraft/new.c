// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小辛[2;37;0m[2;37;0m", ({"news"}));        
        set("gender", "男性");                
        set("long", "小辛[2;37;0m
它是小新的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "new");
        set("owner_name", "小新");
        set_temp("owner", "new");
        set_temp("owner_name", "小新");
        ::setup();
}
