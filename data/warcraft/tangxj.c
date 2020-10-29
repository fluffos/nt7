// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"tiger"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是唐小嘉的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tangxj");
        set("owner_name", "唐小嘉");
        set_temp("owner", "tangxj");
        set_temp("owner_name", "唐小嘉");
        ::setup();
}
