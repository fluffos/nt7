// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("矿石[2;37;0m[2;37;0m", ({"pifengalong"}));        
        set("gender", "男性");                
        set("long", "喔唷[2;37;0m
它是披风之库的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pifenga");
        set("owner_name", "披风之库");
        set_temp("owner", "pifenga");
        set_temp("owner_name", "披风之库");
        ::setup();
}
