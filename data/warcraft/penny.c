// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m木瓜[2;37;0m[2;37;0m", ({"mugua"}));        
        set("gender", "男性");                
        set("long", "大木瓜大木瓜大木瓜[2;37;0m
它是天蝎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "penny");
        set("owner_name", "天蝎");
        set_temp("owner", "penny");
        set_temp("owner_name", "天蝎");
        ::setup();
}
