inherit NPC;
string *first_name = ({
 "赵","何","谢","李","苏","吴","郑","文","张","陈", "刘","林","樊" }); 
string *name_words = ({ 
"可","小","灵","燕","若","花","蓉","若","云","翠","丽","馨","云","香",
"凝","美","香","兰","玉","环",});
string *color_title = ({
"青带女教众","红带女教众","白带女教众","蓝带女教众","紫带女教众","绿带女教众",
"黄带女教众","金带女教众","银带女教众","黑带女教众", });
void create()
{
        string name;
        name = first_name[random(sizeof(first_name))];
        name += name_words[random(sizeof(name_words))]; 
        if( random(10) > 4 ) 
        name += name_words[random(sizeof(name_words))];
        set_name(name, ({"nu jiaozhong", "jiaozhong", "nu"}));
        set("title", color_title[random(sizeof(color_title))]);
        set("long","这是一名"+query("title", this_object())+"，她正在专心致志地练习功夫。\n");
        set("gender", "女性" );
        set("age", 15+random(20));
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
        set_skill("strike", 25+random(15));
        set_skill("hanbing-mianzhang", 30);
        set_skill("parry", 25+random(15));
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("parry", "hanbing-mianzhang");
        map_skill("strike", "hanbing-mianzhang");
        prepare_skill("strike", "hanbing-mianzhang");
        set("shen_type", 0);
        set("inquiry", ([
                "name": "奴家叫做"+this_object()->name()+"，从十五岁起便投在这里学艺。",
                "rumors": "听说故教主一身浑厚的内力都是得自昆仑山的一次奇遇。",
                "here": "这里是明教总坛，你没事还是不要随便乱转的好。",
                "明教": "问什么问，不懂用help mingjiao吗？！",
        ]));
        setup();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}
