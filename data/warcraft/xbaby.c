// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m可靠仔仔[2;37;0m[2;37;0m", ({"pla"}));        
        set("gender", "男性");                
        set("long", "好的哈哈[2;37;0m
它是小刨冰的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xbaby");
        set("owner_name", "小刨冰");
        set_temp("owner", "xbaby");
        set_temp("owner_name", "小刨冰");
        ::setup();
}
