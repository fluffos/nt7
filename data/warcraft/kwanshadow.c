// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m小红[2;37;0m[2;37;0m", ({"xiaohong"}));        
        set("gender", "女性");                
        set("long", "一只红彤彤的朱雀[2;37;0m
它是小玉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kwanshadow");
        set("owner_name", "小玉");
        set_temp("owner", "kwanshadow");
        set_temp("owner_name", "小玉");
        ::setup();
}
