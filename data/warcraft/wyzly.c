// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("腰杆酸[2;37;0m[2;37;0m", ({"tooly"}));        
        set("gender", "男性");                
        set("long", "腰杆酸[2;37;0m
它是伊卡璐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wyzly");
        set("owner_name", "伊卡璐");
        set_temp("owner", "wyzly");
        set_temp("owner_name", "伊卡璐");
        ::setup();
}
