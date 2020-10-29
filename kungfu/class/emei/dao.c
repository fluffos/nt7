// dao.c 静道师太
#include <command.h>
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("静道师太", ({ "jingdao shitai","jingdao","shitai"}));
        set("long", "她是一位中年出家道姑，道冠高拢，慈眉善目。\n");
        set("gender", "女性");
        set("age", 42);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 21);
        set("int", 22);
        set("con", 22);
        set("dex", 20);

        set("max_qi", 2300);
        set("max_jing", 1200);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jingli", 700);
        set("max_jingli", 700);

        set("combat_exp", 180000);
        set_skill("persuading", 80);
        set_skill("throwing", 80);
        set_skill("force", 120);
        set_skill("dodge", 100);
        set_skill("finger", 110);
        set_skill("parry", 100);
        set_skill("strike", 100);
        set_skill("sword", 120);
        set_skill("blade", 120);
        set_skill("literate", 80);
        set_skill("mahayana", 110);
        set_skill("hand", 120);
        set_skill("jieshou-jiushi", 120);
        set_skill("jinding-zhang", 100);
        set_skill("tiangang-zhi", 100);
        set_skill("yanxing-dao", 120);
        set_skill("zhutian-bu", 100);
        set_skill("emei-jian", 120);
        set_skill("emei-xinfa", 100);
        set_skill("linji-zhuang", 120);
        map_skill("force","linji-zhuang");
        map_skill("finger","tiangang-zhi");
        map_skill("dodge","zhutian-bu");
        map_skill("strike","jinding-zhang");
        map_skill("blade","yanxing-dao");
        map_skill("hand", "jieshou-jiushi");
        map_skill("sword", "emei-jian");
        map_skill("parry","yanxing-dao");

        create_family("峨嵋派", 4, "弟子");

        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        command ("say 阿弥陀佛！贫尼不收弟子。\n");
        return;
}
