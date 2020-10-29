// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m当[1;32m里[1;36m个[1;31m当[2;37;0m[2;37;0m", ({"dang"}));        
        set("gender", "男性");                
        set("long", "当哩个来当，当里个当，当里个当来当里个当！[2;37;0m
它是武当的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wudang");
        set("owner_name", "武当");
        set_temp("owner", "wudang");
        set_temp("owner_name", "武当");
        ::setup();
}
