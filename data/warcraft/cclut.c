// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m九天玄女[2;37;0m[2;37;0m", ({"lut"}));        
        set("gender", "女性");                
        set("long", "一只上古神兽。[2;37;0m
它是慕容九刃的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cclut");
        set("owner_name", "慕容九刃");
        set_temp("owner", "cclut");
        set_temp("owner_name", "慕容九刃");
        ::setup();
}
