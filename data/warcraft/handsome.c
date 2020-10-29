// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m酷[2;37;0m[1;33m到[1;35m掉渣[2;37;0m[2;37;0m", ({"forever"}));        
        set("gender", "男性");                
        set("long", "酷有很多种 @_@![2;37;0m
它是酷有嗯种的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "handsome");
        set("owner_name", "酷有嗯种");
        set_temp("owner", "handsome");
        set_temp("owner_name", "酷有嗯种");
        ::setup();
}
