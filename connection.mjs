import { Sequelize } from "sequelize";

const DATABASE_NAME = "planta";
const DATABASE_USERNAME = "root";
const DATABASE_PWD = "";
const DATABASE_HOST = "localhost";
const DATABASE_PORT = 3306;

const connection = new Sequelize(DATABASE_NAME, DATABASE_USERNAME, DATABASE_PWD, {
    host: DATABASE_HOST,
    port: DATABASE_PORT,
    dialect: 'mysql',
    logging: false
})

try{
    connection.authenticate()
    console.log("Conexión a la base de datos exitosa");
}catch(e){
    console.error("Error al conectarse a la base de datos:")
    console.error(e);
}

export default connection;