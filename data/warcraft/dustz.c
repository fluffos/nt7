// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m客官[1;33m[2;37;0m[2;37;0m", ({"dust"}));        
        set("gender", "男性");                
        set("long", "一名瘦弱的客官[2;37;0m
它是客官别逃的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dustz");
        set("owner_name", "客官别逃");
        set_temp("owner", "dustz");
        set_temp("owner_name", "客官别逃");
        ::setup();
}
