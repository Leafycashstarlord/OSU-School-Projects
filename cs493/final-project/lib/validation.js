function validateAgainstSchema(doc, schema){
    return doc && Object.keys(schema).every(
        key => schema[key].allowNull || doc[key]
    )
}

exports.validateAgainstSchema = validateAgainstSchema

function extractValidFields(obj, schema) {
    let validObj = {};
    Object.keys(schema).forEach((field) => {
        if (obj[field] != undefined) {
        validObj[field] = obj[field];
        }
    });
    return validObj;
};

exports.extractValidFields = extractValidFields