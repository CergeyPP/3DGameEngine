Проект "3D Engine".
Разработка началась в 2019г., проект заморожен.
 
Описание проекта

Проект представляет собой графико-логический движок, объекты которого могут иметь различные компоненты. Объект может содержать в себе различные компоненты, такие как: 
источник света(реализованы 2 вида источников света: точечный и глобальный), модель, скелет человека с готовыми анимациями, объект действия(actor), или же простой мэш куба. 

Объекты могут наследоваться друг от друга, тем самым создавая объекты со сложной иерархией.

Каждый мэш имеет свой материал: текстуры и свойства материала для каждого объекта могут быть разными. Материал света также может отличаться от источника к источнику. 

Скелетная анимация реализована через создание костей и привязывание их к объекту анимации(Pawn object). В объект анимации уже вписаны базовые анимации передвижения. 
К костям можно привязать другие объекты для создания интересных персонажей.

Технологии, используемые в проекте:
- Язык программирования С++, в том числе использование ООП
- Библиотека STL: контейнеры для хранения данных об объектах на сцене.
- Библиотека GLFW и GLEW для отрисовки 3D графики
- GLSL для написания вершинных и фрагментных шейдеров
- Библиотека Assimp для загрузки моделей
- DevIL библиотека для загрузки текстур
