//huyuan.c

inherit "/inherit/char/huyuan.c";

void create()
{
    if(!restore())
    {
        set("long", "此人精气内敛，一副深藏不露的模样。\n");
        set("gender", "男性");
        set("attitude", "friend");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("age", 30);
        set("per", 20 + random(20));
        set("set_skill/level", 600);
        set("set_skill/owner", "HOUSE_D");
        set("owner", "OWNER");
        set("owner_name", "某人");
    }
    if(!query("modify/name"))
        set_name(query("owner_name") + "的护院", ({ "hu yuan", "huyuan" }));
    else
        set_name(query("modify/name"), ({ "hu yuan", "huyuan" }));

    setup();
    add_all_settings();
}
