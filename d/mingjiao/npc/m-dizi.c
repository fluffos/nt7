inherit NPC;
string *first_name = ({
"赵","钱","孙","李","周","吴","郑","王","张","陈", "刘","林" }); 
string *name_words = ({
"顺","昌","振","发","财","俊","彦","良","志","忠", "孝","雄","益","添","金",
"辉","长","盛","胜","进","安","福","同","满", "富","万","龙","隆","祥","栋","国","亿","寿","杨" });
string *color_title = ({
"青带男教众","红带男教众","白带男教众","蓝带男教众","紫带男教众","绿带男教众",
"黄带男教众","金带男教众","银带男教众","黑带男教众", });

void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))]; 
        if( random(10) > 4 ) 
        name += name_words[random(sizeof(name_words))];
        set_name(name, ({"nan jiaozhong", "jiaozhong", "nan"}) );
        set("title", color_title[random(sizeof(color_title))]);
        set("long","这是一名"+query("title", this_object())+"，他正在专心致志地练习功夫。\n");
        set("gender", "男性" );
        set("age", 16+random(20));
        set("attitude", "peaceful");
        set("str",15+random(13));
        set("int",20);
        set("con",15+random(12));
        set("dex",15+random(10));
        set("max_qi", 300+random(200));
        set("max_jing", 200)+random(200);
        set("neili", 250+random(200));
        set("max_neili", 250+random(200));
        set("combat_exp", random(6000)+6000);
        set_skill("force", 25+random(15));
        set_skill("shenghuo-shengong", 30);
        set_skill("dodge", 25+random(15));
        set_skill("piaoyi-shenfa", 30);
        set_skill("hand", 25+random(15));
        set_skill("sougu-yingzhua", 30);
        set_skill("parry", 25+random(15));
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("parry", "sougu-yingzhua");
        map_skill("hand", "sougu-yingzhua");
        prepare_skill("hand", "sougu-yingzhua");
        set("inquiry", ([
                "name": "在下明尊座下末进弟子，从十六岁起便投在这里学艺。",
                "rumors": "听说故教主一身浑厚的内力都是得自昆仑山的一次奇遇。",
                "here": "这里是明教总坛，你没事还是不要随便乱转的好。",
                "明教": "问什么问，不懂用help mingjiao吗？！",
        ]));
        setup();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}
