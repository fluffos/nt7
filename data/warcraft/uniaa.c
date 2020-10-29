// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兔一一[2;37;0m[2;37;0m", ({"tua"}));        
        set("gender", "男性");                
        set("long", "这是一只可爱的大兔子[2;37;0m
它是叶一一的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "uniaa");
        set("owner_name", "叶一一");
        set_temp("owner", "uniaa");
        set_temp("owner_name", "叶一一");
        ::setup();
}
