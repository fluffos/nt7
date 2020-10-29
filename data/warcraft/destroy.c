// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m穷奇[2;37;0m[2;37;0m", ({"afraid"}));        
        set("gender", "男性");                
        set("long", "毁信恶忠，崇饰恶言，以御魑魅![2;37;0m
它是劫渡的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "destroy");
        set("owner_name", "劫渡");
        set_temp("owner", "destroy");
        set_temp("owner_name", "劫渡");
        ::setup();
}
