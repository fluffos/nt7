// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白白虎[2;37;0m[2;37;0m", ({"baibaihu"}));        
        set("gender", "男性");                
        set("long", "一只白虎，就这样。[2;37;0m
它是艾文金吉的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ivan");
        set("owner_name", "艾文金吉");
        set_temp("owner", "ivan");
        set_temp("owner_name", "艾文金吉");
        ::setup();
}
