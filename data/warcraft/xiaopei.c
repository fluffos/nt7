// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m仙子[2;37;0m[2;37;0m", ({"bag"}));        
        set("gender", "男性");                
        set("long", "一只张牙舞爪的小白龙[2;37;0m
它是花无缺的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaopei");
        set("owner_name", "花无缺");
        set_temp("owner", "xiaopei");
        set_temp("owner_name", "花无缺");
        ::setup();
}
