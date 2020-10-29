// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是小瘟神的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ijtvdw");
        set("owner_name", "小瘟神");
        set_temp("owner", "ijtvdw");
        set_temp("owner_name", "小瘟神");
        ::setup();
}
