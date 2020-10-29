// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"dsy"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是慕容百胜的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dsydxlc");
        set("owner_name", "慕容百胜");
        set_temp("owner", "dsydxlc");
        set_temp("owner_name", "慕容百胜");
        ::setup();
}
