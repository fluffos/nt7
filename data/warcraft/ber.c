// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m老白[2;37;0m[2;37;0m", ({"hei"}));        
        set("gender", "男性");                
        set("long", "嘿嘿[2;37;0m
它是宁缺的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ber");
        set("owner_name", "宁缺");
        set_temp("owner", "ber");
        set_temp("owner_name", "宁缺");
        ::setup();
}
