// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小溪龙[2;37;0m[2;37;0m", ({"aaaaa"}));        
        set("gender", "男性");                
        set("long", "一条小河里的龙[2;37;0m
它是血无痕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xwh");
        set("owner_name", "血无痕");
        set_temp("owner", "xwh");
        set_temp("owner_name", "血无痕");
        ::setup();
}
