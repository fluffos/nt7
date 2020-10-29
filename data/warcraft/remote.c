// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m天丛云[2;37;0m[2;37;0m", ({"remotez"}));        
        set("gender", "男性");                
        set("long", "天丛云[2;37;0m
它是天罪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "remote");
        set("owner_name", "天罪");
        set_temp("owner", "remote");
        set_temp("owner_name", "天罪");
        ::setup();
}
