// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m客官[1;33m[2;37;0m[2;37;0m", ({"keguan"}));        
        set("gender", "男性");                
        set("long", "一个瘦弱的客官[2;37;0m
它是客官饶命的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dustc");
        set("owner_name", "客官饶命");
        set_temp("owner", "dustc");
        set_temp("owner_name", "客官饶命");
        ::setup();
}
