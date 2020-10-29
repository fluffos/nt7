// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m凰[2;37;0m[2;37;0m", ({"phinex"}));        
        set("gender", "男性");                
        set("long", "黑秋秋~~黑秋秋[2;37;0m
它是萧邦的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kknds");
        set("owner_name", "萧邦");
        set_temp("owner", "kknds");
        set_temp("owner_name", "萧邦");
        ::setup();
}
