// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m玉字二号丸[2;37;0m[2;37;0m", ({"yqb"}));        
        set("gender", "男性");                
        set("long", "lkjjjjjjjjjjjjjj[2;37;0m
它是东方玉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yubqing");
        set("owner_name", "东方玉");
        set_temp("owner", "yubqing");
        set_temp("owner_name", "东方玉");
        ::setup();
}
