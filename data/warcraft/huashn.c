// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤日雀[2;37;0m[2;37;0m", ({"chirwue"}));        
        set("gender", "女性");                
        set("long", "一飞冲天[2;37;0m
它是花生女的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huashn");
        set("owner_name", "花生女");
        set_temp("owner", "huashn");
        set_temp("owner_name", "花生女");
        ::setup();
}
