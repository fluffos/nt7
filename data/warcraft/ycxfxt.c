// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是铁游夏的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ycxfxt");
        set("owner_name", "铁游夏");
        set_temp("owner", "ycxfxt");
        set_temp("owner_name", "铁游夏");
        ::setup();
}
