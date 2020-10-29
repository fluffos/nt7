// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"bhu"}));        
        set("gender", "男性");                
        set("long", "$HIW$白虎[2;37;0m
它是说不得的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xde");
        set("owner_name", "说不得");
        set_temp("owner", "xde");
        set_temp("owner_name", "说不得");
        ::setup();
}
