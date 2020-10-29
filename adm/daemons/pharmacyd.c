// Pharmacy daemon(preparing and dispensing drugs)
// By landis@MYTH
// 2002.05.09
// last update 2002.08.23

//  此物件负责处理所有药物相关的事务，包括：
//
//  1.根据药性获得相应的药材。
//  2.核对处方将药材转化为药物。
//  3.处理及保存新的处方数据。
//  4.将药材或药物的名称与编号互相转换。

/***********************************************************
保存药物编号及对应名称的映射如下：
mapping data = ([
        "herb" : ([
                0 : "甘草",
                1 : "沉香",
                ]),
        "medicine" : ([
                0 : "玄黄紫清丹",
                1 : "甘草润肺散",
                ]),
        ]);

保存处方的映射如下：
mapping prescription = ([
        1, 2, 3 : 1,
        2, 3, 4 : 2,
        ]);

保存药材相关信息的映射如下：
mapping relation = ([
        0 : ([
                "eng"  : ({"gan cao", "cao"}),
                "unit" : "棵",
                "desc" : "一棵紫红色的小草，看起来煞是可爱。",
                ]),
        ]);
***********************************************************/

#include <ansi.h>

inherit F_DBASE;
inherit F_SAVE;

mapping data;
mapping prescription;

mapping relation;

void initialize();
int register_all_medicine();

void create()
{
        seteuid(ROOT_UID);
        initialize(); // 初始化，包括载入数据，刷新映射等

        set("channel_id", "制药精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "制药系统已经启动。");
}

// 初始化，包括载入数据，刷新映射等
void initialize()
{
        restore();        

        if (! mapp(data))
        {
                data = allocate_mapping(2);
                data["herb"] = allocate_mapping(50);
                data["medicine"] = allocate_mapping(50);
        }

        if (! sizeof(data["medicine"]))
                register_all_medicine();

        if (! mapp(prescription))
                prescription = allocate_mapping(50);

        if (! mapp(relation))
                relation = allocate_mapping(50);
}

void remove() { save(); }

string query_save_file() { return DATA_DIR "pharmacyd"; }

/*********************************************************************
                       以下为增加、删除数据的接口
*********************************************************************/

// 注册药材id及对应中文名称
int register_herb(int id, string name)
{
        object ob;
        string file;

/*
        ob = previous_object();

        if (! is_root(ob) || geteuid(ob) != "Clone")
                error("Pharmacyd:Herb Registration conflict, Access denied.\n");
*/

        if (! mapp(data))
                data = ([ "herb" : ([ id : name ]) ]);
        else if (! mapp(data["herb"]))
                data["herb"] = ([ id : name ]);
        else
                data["herb"][id] = name;

        return 1;
}

// 设置药材的基本信息
int set_relation(int id, mapping rt)
{
        mapping map;

        relation[id] = allocate_mapping(3);

        map = relation[id];

        if (! mapp(map) || ! sizeof(map))
                map = ([ "eng" : rt["eng"] ]);
        else
                map["eng"]  = rt["eng"];

        map["unit"] = rt["unit"];
        map["desc"] = rt["desc"];

        relation[id] = map;

        return 1;
}

// 注册药物id及对应名称(由药物物件取得)
int register_medicine(int id)
{
        object obj;
        string file, name;

//      if (previous_object() != this_object())
//              return 0;

        file = id < 10 ? "0%d" : "%d";
        file = sprintf(file, id);
        file = MEDICINE_DIR(file);

        call_other(file, "???");
        obj = find_object(file);
        name = filter_color(obj->query("name"));

        if (geteuid(obj) != "Clone")
                error("Pharmacyd:Medicine Registration conflict, Access denied.\n");

        if (! mapp(data))
                data = ([ "medicine" : ([ id : name ]) ]);
        else if (! mapp(data["medicine"]))
                data["medicine"] = ([ id : name ]);
        else
                data["medicine"][id] = name;

        return 1;
}

// 注册所有药物
int register_all_medicine()
{
        int i, id;
        string *dir;

        dir = get_dir(MEDICINE_DIR(""));

        if (! dir || ! sizeof(dir)) return 0;
        for (i = 0; i < sizeof(dir); i++)
        {
                if (! sscanf(dir[i], "%d.c", id))
                        continue;

                register_medicine(id);
        }

        return 1;
}

// 注销某一药材或药物
int unregister(string type, int id)
{

//      if (previous_object() && geteuid(previous_object()) != ROOT_UID)
//	        return 0;

        if (type != "herb" && type != "medicine")
                return notify_fail("Pharmacyd:Wrong type, Access denied.\n");

        if (mapp(data) && mapp(data[type]))
                map_delete(data[type], id);

        return 1;
}

// 增加处方数据
int add_prescription(int *herbs, string medicine)
{
        if (! mapp(prescription))
                prescription = ([ herbs : medicine ]);
        else
                prescription[herbs] = medicine;

        return 1;
}

// 删除处方数据
int delete_prescription(int *herbs)
{
        if (! mapp(prescription) || undefinedp(prescription[herbs]))
                return 0;

        map_delete(prescription, herbs);
        return 1;
}

/*********************************************************************
                       以下为供外部调用的查询接口
*********************************************************************/

// 返回该药材的基本信息，在药材初始化时调用
mapping query_relation(int id) { return relation[id]; }

// 通过药材或药物名查询编号
int check_id(string name)
{
        int loc;
        int *key;
        string *value;

        key   = keys(data["herb"]);
        value = values(data["herb"]);
        loc   = member_array(name, value);

        if (loc == -1)
        {
                key   = keys(data["medicine"]);
                value = values(data["medicine"]);
                loc   = member_array(value, name);
        }

        return key[loc];
}

// 通过类型(药材或药物)及id查询中文名称
string check_name(string type, int id)
{
        mapping fname;

        if (type != "herb" && type != "medicine")
                error("Pharmacyd:Wrong Check Type,Access denied.\n");

        fname = data[type];
        return fname[id];
}

// 查询该类型(药材或药物)某一id是否已注册
int already_registerd(string type, int id)
{
        if (type != "herb" && type != "medicine")
                return notify_fail("查询类型错误！\n");

        return undefinedp(data[type][id]) == 0;
}

/*********************************************************************
                       以下为调用查看数据列表的接口
*********************************************************************/

// 返回药材列表
string list_herb()
{
        int i;
        string *key;
        string line;
        mapping herbs;

        herbs = data["herb"];

        if (! mapp(herbs) || ! sizeof(herbs))
                return "目前尚未完成药材数据构造！\n";

        line  = WHT"\n目前已收集的药材数据如下：\n\n"NOR;
        key   = keys(herbs);
        key   = sort_array(key, 1);

        for(i = 0; i < sizeof(key); i++)
        {
                line += sprintf(CYN"%2d", key[i]);
                line += "　　";
                line += sprintf(WHT"%-10s"NOR, herbs[key[i]]);

                line += (i<4 || i%4) ? "　" : "\n";
        }

        return line;
}

// 返回药物列表
string list_medicine()
{
        int i;
        string *key;
        string line;
        mapping medicines;

        medicines = data["medicine"];

        if (! mapp(medicines) || ! sizeof(medicines))
                return "目前尚未完成药物数据构造！\n";

        line  = WHT"\n目前已收集的药物数据如下：\n\n"NOR;
        key   = keys(medicines);
        key   = sort_array(key, 1);

        for(i = 0; i < sizeof(key); i++)
        {
                line += sprintf(CYN"%2d", key[i]);
                line += "　　";
                line += sprintf(WHT"%-10s"NOR, medicines[key[i]]);

                line += (i<4 || i%4) ? "　" : "\n";
        }

        return line;
}

// 返回处方列表
string list_prescription()
{
        int i;
        string line;
        int *key, *value;

        if (! mapp(prescription) || ! sizeof(prescription))
                return "目前尚无药方数据可供查询！\n";

        line  = "";
        key   = keys(prescription);
        value = values(prescription);

        for (i=0; i<sizeof(key); i++)
        {
                foreach(int id in key[i])
                        line += sprintf(HIW"%-8s", check_name("herb", id));

                line += sprintf(HIC"：%-20s", check_name("medicine", value[i]));
                line += "\n" NOR;
        }

        return line;
}

/*********************************************************************
                       以下为按要求生成药材的接口

                其中，每件药材的属性都是唯一的，形式如下：

                味性(Taste)     ：苦、咸、酸、甘、辛
                药性(Officinal) ：寒、凉、平、温、热
                毒性(toXicity)  ：有、无

                所以，以 {x,y,z} 形式的数组对应唯一一种药
                材，总数即为 5x5x2 = 50 种。

*********************************************************************/

// 根据属性计算编号，创建药材
object build_herb(int *prop)
{
        int num;
        int tp, op, xp;
        object ob;
        string name;

        tp = prop[0];
        op = prop[1];
        xp = prop[2];

        if (tp < 0 || op < 0 || xp < 0 ||
            tp > 4 || op > 4 || xp > 1 ||
            sizeof(prop) > 3)
                error("Pharmacyd:Wrong Herb Prop.\n");

        // 算法为 10*x + 2*y + z 即可得到该药材的唯一编号。
        num  = xp;
        num += op * 2;
        num += tp * 10;

        name = data["herb"][num];

        if (! stringp(name))
                error("Pharmacyd:Fail in Loading Herb object.\n");

        ob = new(HERB_OB);               // 建立原型
        ob->initialize(num, name, prop); // 初始化

        return ob;
}

// 根据编号创建药材
object clone_herb(int id)
{
        object ob;
        string name;
        int *prop;
        int tp, op, xp;

        name = data["herb"][id];

        if (! stringp(name))
                error("Pharmacyd:Fail in Loading Herb object.\n");

        tp = id / 10;
        op = (id%10) / 2;
        xp = id - (tp * 10) - (op * 2);

        prop = ({ tp, op , xp });

        ob = new(HERB_OB);              // 建立原型
        ob->initialize(id, name, prop); // 初始化

        return ob;
}

/*********************************************************************
                       以下为按处方生成药物的接口

                每次制药的成功率大约为50%，
                能否制药的能力限制暂时未予以考虑。
                若制药失败，有一定机会得到 催化剂 炼金水 黄金
                中的一种，否则将得到废料。

*********************************************************************/

// 核对处方将药材转化为药物
object build_medicine(object *herbs)
{
        object obj;
        int *id_list;
        int i, id, flag;
        string *recipe;
        string bname, name;

        id_list = allocate(sizeof(herbs));

        for (i = 0; i < sizeof(herbs); i++)
        {
                if (herbs[i]->is_activator()) { flag = 1; continue; }
                bname = base_name(herbs[i]);
                if (bname != HERB_OB) continue;
                id_list[i] = id;
        }

        foreach (recipe in keys(prescription))
        {
                if (recipe - id_list == ({ }) &&
                    flag ? 1 : random(10) > 5)
                {
                        name = sprintf("%d", prescription[recipe]);
                        name = MEDICINE_DIR(name);

                        for (i = 0; i < sizeof(herbs); i++)
                                destruct(herbs[i]);

                        call_other(name, "???");
                        if (! objectp(find_object(name)))
                                error("Pharmacyd:Fail in Loading Medicine object.\n");

                        return new(name);;
                } else
                {
                        switch (random(100))
                        {
                                case 84: obj = new(GOLD_OB); break;
                                case 11: obj = new(MEDICINE_DIR("activator")); break;
                                case 30: obj = new(MEDICINE_DIR("elixir")); break;
                                default: obj = new(MEDICINE_DIR("waste"));
                        }

                        return obj;
                }
        }
}
