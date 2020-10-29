// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m行星海洋[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "行星海洋[2;37;0m
它是阿基里斯的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "achilles");
        set("owner_name", "阿基里斯");
        set_temp("owner", "achilles");
        set_temp("owner_name", "阿基里斯");
        ::setup();
}
