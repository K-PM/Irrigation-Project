import { Model, DataTypes } from "sequelize";
import connection from "./connection.mjs";

class Logs extends Model { }

Logs.init({
    id: {
        type: DataTypes.BIGINT,
        primaryKey: true,
        autoIncrement: true
    },
    humA: {
        type: DataTypes.STRING,
        allowNull: false
    },
    humD: {
        type: DataTypes.STRING,
        allowNull: false
    },
    riego: {
        type: DataTypes.STRING,
        allowNull: false
    }

},{
    tableName:"logs",
    sequelize:connection
})

Logs.sync();

export default Logs