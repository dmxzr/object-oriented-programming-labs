#include <gtest/gtest.h>
#include "lib/AgencyTable.hpp"
#include "lib/PublishingMedia.hpp"
#include "lib/RadioStation.hpp"
#include "lib/TVCompany.hpp"
#include "lib/Agency.hpp"
#include "lib/TestAgency.hpp"
#include "lib/Menu.hpp"

// Тест для проверки добавления и поиска агентств
TEST(AgencyTableTest, AddAndFindAgency) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    RadioStation* rs = new RadioStation("Radio1", "Music", "456", "St. Petersburg", {{"FM", "101.5"}, {"AM", "800"}});
    TVCompany* tv = new TVCompany("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");

    // Добавляем агентства в таблицу
    table.add(pm);
    table.add(rs);
    table.add(tv);

    // Проверяем, что агентства можно найти
    EXPECT_EQ(table.find("Print1"), pm);
    EXPECT_EQ(table.find("Radio1"), rs);
    EXPECT_EQ(table.find("TV1"), tv);

    // Удаляем агентства
    delete pm;
    delete rs;
    delete tv;
}

// Тест для проверки удаления агентств
TEST(AgencyTableTest, RemoveAgency) {
    AgencyTable table;

    // Создаем агентство
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);

    // Добавляем агентство в таблицу
    table.add(pm);

    // Удаляем агентство
    EXPECT_TRUE(table.remove("Print1"));

    // Проверяем, что агентство удалено
    EXPECT_EQ(table.find("Print1"), nullptr);

    // Удаляем агентство
    delete pm;
}

// Тест для проверки подсчета агентств по регионам
TEST(AgencyTableTest, CountAgenciesByRegion) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);
    RadioStation* rs = new RadioStation("Radio1", "Music", "456", "St. Petersburg", {{"FM", "101.5"}, {"AM", "800"}});
    TVCompany* tv = new TVCompany("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);
    table.add(rs);
    table.add(tv);

    // Подсчитываем агентства по регионам
    auto regionCount = table.countAgenciesByRegion();

    // Проверяем количество агентств в каждом регионе
    EXPECT_EQ(regionCount["Moscow"], 2);
    EXPECT_EQ(regionCount["St. Petersburg"], 1);
    EXPECT_EQ(regionCount["Novosibirsk"], 1);

    // Удаляем агентства
    delete pm1;
    delete pm2;
    delete rs;
    delete tv;
}

// Тест для проверки метода get_size
TEST(AgencyTableTest, GetSize) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);

    // Проверяем размер таблицы
    EXPECT_EQ(table.get_size(), 2);

    // Удаляем агентства
    delete pm1;
    delete pm2;
}

// Тест для проверки метода get_capacity
TEST(AgencyTableTest, GetCapacity) {
    AgencyTable table(10);

    // Проверяем емкость таблицы
    EXPECT_EQ(table.get_capacity(), 10);
}

// Тест для проверки метода get_table
TEST(AgencyTableTest, GetTable) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);

    // Проверяем, что таблица не пуста
    EXPECT_NE(table.get_table(), nullptr);

    // Удаляем агентства
    delete pm1;
    delete pm2;
}

// Тест для проверки метода getEntry
TEST(AgencyTableTest, GetEntry) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);

    // Проверяем, что записи в таблице существуют
    EXPECT_NE(table.getEntry(0), nullptr);
    EXPECT_NE(table.getEntry(1), nullptr);

    // Удаляем агентства
    delete pm1;
    delete pm2;
}

// Тест для проверки метода insert
TEST(AgencyTableTest, Insert) {
    AgencyTable table;

    // Создаем агентство
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);

    // Вставляем агентство в таблицу
    table.insert(pm->get_name().c_str(), pm);

    // Проверяем, что агентство можно найти
    EXPECT_EQ(table.find("Print1"), pm);

    // Удаляем агентство
    delete pm;
}

// Тест для проверки метода search
TEST(AgencyTableTest, Search) {
    AgencyTable table;

    // Создаем агентство
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);

    // Добавляем агентство в таблицу
    table.add(pm);

    // Проверяем, что агентство можно найти
    EXPECT_EQ(table.search("Print1"), pm);

    // Удаляем агентство
    delete pm;
}

// Тесты для класса Agency

// Тест для проверки конструктора класса Agency
TEST(AgencyTest, Constructor) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    EXPECT_EQ(agency.get_name(), "TestAgency");
    EXPECT_EQ(agency.get_profile(), "News");
    EXPECT_EQ(agency.get_license_number(), "12345");
    EXPECT_EQ(agency.get_location(), "Moscow");
}

// Тест для проверки метода get_name
TEST(AgencyTest, GetName) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    EXPECT_EQ(agency.get_name(), "TestAgency");
}

// Тест для проверки метода get_profile
TEST(AgencyTest, GetProfile) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    EXPECT_EQ(agency.get_profile(), "News");
}

// Тест для проверки метода get_license_number
TEST(AgencyTest, GetLicenseNumber) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    EXPECT_EQ(agency.get_license_number(), "12345");
}

// Тест для проверки метода get_location
TEST(AgencyTest, GetLocation) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    EXPECT_EQ(agency.get_location(), "Moscow");
}

// Тест для проверки метода set_profile
TEST(AgencyTest, SetProfile) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    agency.set_profile("UpdatedProfile");
    EXPECT_EQ(agency.get_profile(), "UpdatedProfile");
}

// Тест для проверки метода set_location
TEST(AgencyTest, SetLocation) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    agency.set_location("UpdatedLocation");
    EXPECT_EQ(agency.get_location(), "UpdatedLocation");
}

// Тест для проверки метода set_license_number
TEST(AgencyTest, SetLicenseNumber) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    agency.set_license_number("67890");
    EXPECT_EQ(agency.get_license_number(), "67890");
}

// Тест для проверки метода display_info
TEST(AgencyTest, DisplayInfo) {
    TestAgency agency("TestAgency", "News", "12345", "Moscow");
    testing::internal::CaptureStdout();
    agency.display_info();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Name: TestAgency"), std::string::npos);
    EXPECT_NE(output.find("Profile: News"), std::string::npos);
    EXPECT_NE(output.find("License Number: 12345"), std::string::npos);
    EXPECT_NE(output.find("Location: Moscow"), std::string::npos);
}



// Тесты для класса PublishingMedia

// Тест для проверки конструктора класса PublishingMedia
TEST(PublishingMediaTest, Constructor) {
    PublishingMedia pm("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    EXPECT_EQ(pm.get_name(), "Print1");
    EXPECT_EQ(pm.get_profile(), "News");
    EXPECT_EQ(pm.get_license_number(), "123");
    EXPECT_EQ(pm.get_location(), "Moscow");
    EXPECT_EQ(pm.get_period(), (std::vector<std::string>{"Monday", "Wednesday"}));
    EXPECT_EQ(pm.get_circulation(), 10000);
}

// Тест для проверки метода get_type
TEST(PublishingMediaTest, GetType) {
    PublishingMedia pm("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    EXPECT_EQ(pm.get_type(), "PublishingMedia");
}

// Тест для проверки метода get_period
TEST(PublishingMediaTest, GetPeriod) {
    PublishingMedia pm("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    EXPECT_EQ(pm.get_period(), (std::vector<std::string>{"Monday", "Wednesday"}));
}

// Тест для проверки метода get_circulation
TEST(PublishingMediaTest, GetCirculation) {
    PublishingMedia pm("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    EXPECT_EQ(pm.get_circulation(), 10000);
}

// Тест для проверки метода set_period
TEST(PublishingMediaTest, SetPeriod) {
    PublishingMedia pm("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    pm.set_period({"Tuesday", "Thursday"});
    EXPECT_EQ(pm.get_period(), (std::vector<std::string>{"Tuesday", "Thursday"}));
}

// Тест для проверки метода set_circulation
TEST(PublishingMediaTest, SetCirculation) {
    PublishingMedia pm("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    pm.set_circulation(15000);
    EXPECT_EQ(pm.get_circulation(), 15000);
}


// Тест для проверки конструктора класса TVCompany
TEST(TVCompanyTest, Constructor) {
    TVCompany tv("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");
    EXPECT_EQ(tv.get_name(), "TV1");
    EXPECT_EQ(tv.get_profile(), "Entertainment");
    EXPECT_EQ(tv.get_license_number(), "789");
    EXPECT_EQ(tv.get_location(), "Novosibirsk");
    EXPECT_EQ(tv.get_channel(), "Channel 1");
}

// Тест для проверки метода get_type
TEST(TVCompanyTest, GetType) {
    TVCompany tv("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");
    EXPECT_EQ(tv.get_type(), "TVCompany");
}

// Тест для проверки метода get_channel
TEST(TVCompanyTest, GetChannel) {
    TVCompany tv("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");
    EXPECT_EQ(tv.get_channel(), "Channel 1");
}

// Тест для проверки метода set_channel
TEST(TVCompanyTest, SetChannel) {
    TVCompany tv("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");
    tv.set_channel("Channel 2");
    EXPECT_EQ(tv.get_channel(), "Channel 2");
}



// Тест для проверки конструктора класса RegionIterator
TEST(RegionIteratorTest, Constructor) {
    std::vector<Agency*> agencies = {
        new TestAgency("Agency1", "Profile1", "License1", "Location1"),
        new TestAgency("Agency2", "Profile2", "License2", "Location2"),
        new TestAgency("Agency3", "Profile3", "License3", "Location1")
    };

    RegionIterator iterator(agencies);

    // Удаляем агентства
    for (auto agency : agencies) {
        delete agency;
    }
}

// Тест для проверки метода hasNext
TEST(RegionIteratorTest, HasNext) {
    std::vector<Agency*> agencies = {
        new TestAgency("Agency1", "Profile1", "License1", "Location1"),
        new TestAgency("Agency2", "Profile2", "License2", "Location2"),
        new TestAgency("Agency3", "Profile3", "License3", "Location1")
    };

    RegionIterator iterator(agencies);

    EXPECT_TRUE(iterator.hasNext());
    iterator.next();
    EXPECT_TRUE(iterator.hasNext());
    iterator.next();
    EXPECT_FALSE(iterator.hasNext());

    // Удаляем агентства
    for (auto agency : agencies) {
        delete agency;
    }
}

// Тест для проверки метода next
TEST(RegionIteratorTest, Next) {
    std::vector<Agency*> agencies = {
        new TestAgency("Agency1", "Profile1", "License1", "Location1"),
        new TestAgency("Agency2", "Profile2", "License2", "Location2"),
        new TestAgency("Agency3", "Profile3", "License3", "Location1")
    };

    RegionIterator iterator(agencies);

    EXPECT_TRUE(iterator.hasNext());
    auto result = iterator.next();
    EXPECT_EQ(result.first, "Location1");
    EXPECT_EQ(result.second, 2);

    EXPECT_TRUE(iterator.hasNext());
    result = iterator.next();
    EXPECT_EQ(result.first, "Location2");
    EXPECT_EQ(result.second, 1);

    EXPECT_FALSE(iterator.hasNext());

    // Удаляем агентства
    for (auto agency : agencies) {
        delete agency;
    }
}






// Тест для проверки метода getAllAgencies
TEST(AgencyTableTest, GetAllAgencies) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    RadioStation* rs = new RadioStation("Radio1", "Music", "456", "St. Petersburg", {{"FM", "101.5"}, {"AM", "800"}});
    TVCompany* tv = new TVCompany("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");

    // Добавляем агентства в таблицу
    table.add(pm);
    table.add(rs);
    table.add(tv);

    // Получаем все агентства
    std::vector<Agency*> agencies = table.getAllAgencies();

    // Проверяем, что все агентства присутствуют
    EXPECT_NE(std::find(agencies.begin(), agencies.end(), pm), agencies.end());
    EXPECT_NE(std::find(agencies.begin(), agencies.end(), rs), agencies.end());
    EXPECT_NE(std::find(agencies.begin(), agencies.end(), tv), agencies.end());

    // Удаляем агентства
    delete pm;
    delete rs;
    delete tv;
}

// Тест для проверки метода countAgenciesByRegion
TEST(AgencyTableTest, CountAgenciesByRegionNew) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);
    RadioStation* rs = new RadioStation("Radio1", "Music", "456", "St. Petersburg", {{"FM", "101.5"}, {"AM", "800"}});
    TVCompany* tv = new TVCompany("TV1", "Entertainment", "789", "Novosibirsk", "Channel 1");

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);
    table.add(rs);
    table.add(tv);

    // Подсчитываем агентства по регионам
    auto regionCount = table.countAgenciesByRegion();

    // Проверяем количество агентств в каждом регионе
    EXPECT_EQ(regionCount["Moscow"], 2);
    EXPECT_EQ(regionCount["St. Petersburg"], 1);
    EXPECT_EQ(regionCount["Novosibirsk"], 1);

    // Удаляем агентства
    delete pm1;
    delete pm2;
    delete rs;
    delete tv;
}

// Тест для проверки метода getEntry
TEST(AgencyTableTest, GetEntryNew) {
    AgencyTable table;

    // Создаем агентства
    PublishingMedia* pm1 = new PublishingMedia("Print1", "News", "123", "Moscow", {"Monday", "Wednesday"}, 10000);
    PublishingMedia* pm2 = new PublishingMedia("Print2", "News", "124", "Moscow", {"Tuesday", "Thursday"}, 15000);

    // Добавляем агентства в таблицу
    table.add(pm1);
    table.add(pm2);

    // Проверяем, что записи в таблице существуют
    EXPECT_NE(table.getEntry(0), nullptr);
    EXPECT_NE(table.getEntry(1), nullptr);

    // Удаляем агентства
    delete pm1;
    delete pm2;
}

// Тест для проверки метода getCapacity
TEST(AgencyTableTest, GetCapacityNew) {
    AgencyTable table(10);

    // Проверяем емкость таблицы
    EXPECT_EQ(table.getCapacity(), 10);
}






// Тест для проверки конструктора класса Menu
TEST(MenuTest, Constructor) {
    AgencyTable agencies;
    Menu menu(agencies);
    // Конструктор должен быть вызван без ошибок
}

// Тест для проверки метода run
TEST(MenuTest, Run) {
    AgencyTable agencies;
    Menu menu(agencies);
    // Метод run должен быть вызван без ошибок
    menu.run();
}

// Тест для проверки метода display_menu
TEST(MenuTest, DisplayMenu) {
    AgencyTable agencies;
    Menu menu(agencies);
    testing::internal::CaptureStdout();
    menu.display_menu();
    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем, что вывод не пустой
    EXPECT_FALSE(output.empty());
}

// Тест для проверки метода create_agency
TEST(MenuTest, CreateAgency) {
    AgencyTable agencies;
    Menu menu(agencies);
    Agency* agency = menu.create_agency();
    // Проверяем, что созданное агентство не является nullptr
    EXPECT_NE(agency, nullptr);
    delete agency;
}



// Тест для проверки метода modify_agency_info
TEST(MenuTest, ModifyAgencyInfo) {
    AgencyTable agencies;
    Menu menu(agencies);
    Agency* agency = menu.create_agency();
    menu.register_new_agency();
    menu.modify_agency_info();
    // Проверяем, что информация об агентстве изменена
    // Здесь нужно добавить проверку изменений в зависимости от реализации метода
    delete agency;
}

// Тест для проверки метода display_agencies_by_type
TEST(MenuTest, DisplayAgenciesByType) {
    AgencyTable agencies;
    Menu menu(agencies);
    testing::internal::CaptureStdout();
    menu.display_agencies_by_type();
    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем, что вывод не пустой
    EXPECT_FALSE(output.empty());
}

// Тест для проверки метода revoke_license
TEST(MenuTest, RevokeLicense) {
    AgencyTable agencies;
    Menu menu(agencies);
    Agency* agency = menu.create_agency();
    menu.register_new_agency();
    menu.revoke_license();
    // Проверяем, что лицензия отозвана
    // Здесь нужно добавить проверку отзыва лицензии в зависимости от реализации метода
    delete agency;
}

// Тест для проверки метода display_agencies_by_region
TEST(MenuTest, DisplayAgenciesByRegion) {
    AgencyTable agencies;
    Menu menu(agencies);
    testing::internal::CaptureStdout();
    menu.display_agencies_by_region();
    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем, что вывод не пустой
    EXPECT_FALSE(output.empty());
}

// Тест для проверки метода display_all_agencies
TEST(MenuTest, DisplayAllAgencies) {
    AgencyTable agencies;
    Menu menu(agencies);
    testing::internal::CaptureStdout();
    menu.display_all_agencies();
    std::string output = testing::internal::GetCapturedStdout();
    // Проверяем, что вывод не пустой
    EXPECT_FALSE(output.empty());
}





int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
