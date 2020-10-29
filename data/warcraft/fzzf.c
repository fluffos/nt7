// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m糊[1;32m涂[1;33m虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "有点糊涂的小白虎[2;37;0m
它是风中追风的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "fzzf");
        set("owner_name", "风中追风");
        set_temp("owner", "fzzf");
        set_temp("owner_name", "风中追风");
        ::setup();
}
