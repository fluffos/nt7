// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤[37m魔[1;32m龙[2;37;0m[2;37;0m", ({"chimolong"}));        
        set("gender", "男性");                
        set("long", "不灭真身[2;37;0m
它是齐天大魔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "qitdamo");
        set("owner_name", "齐天大魔");
        set_temp("owner", "qitdamo");
        set_temp("owner_name", "齐天大魔");
        ::setup();
}
